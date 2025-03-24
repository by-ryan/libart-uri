namespace art::uri
{

  template<typename Iterator>
  std::optional<uri_t>
  try_parse(Iterator first, Iterator last)
  {
    std::optional<std::string> opt_scheme;
    std::optional<std::string> opt_userinfo;
    std::optional<std::string> opt_host;
    std::optional<std::string> opt_port;
    std::string path;
    std::optional<std::string> opt_query;
    std::optional<std::string> opt_fragment;

    auto try_parse_scheme = [&](auto init)
    {
      auto c = init;

      std::string scheme;
      while (c != last && grammar::is_scheme(*c)) {
        scheme += *c++;
      }

      if (c != last && *c == ':') {
        ++c; // skips ':'
        opt_scheme = std::move(scheme);
        return c;
      }

      return init;
    };

    auto try_parse_userinfo = [&](auto init)
    {
      auto c = init;

      std::string userinfo;

      while (c != last && grammar::is_userinfo(*c)) {
        userinfo += *c++;
      }

      if (c != last && *c == '@') {
        ++c; // skips '@'
        opt_userinfo = std::move(userinfo);
        return c;
      }

      return init;
    };

    auto try_parse_host = [&](auto init)
    {
      auto c = init;

      opt_host = std::string{};

      while (c != last && grammar::is_host(*c)) {
        *opt_host += *c++;
      }

      return c;
    };

    auto try_parse_port = [&](auto init)
    {
      auto c = init;

      if (c != last && *c == ':') {
        ++c; // skips ':'

        opt_port = std::string{};

        while (c != last && grammar::is_digit(*c)) {
          *opt_port += *c++;
        }

        return c;
      }

      return init;
    };

    auto try_parse_authority = [&](auto init)
    {
      auto c = init;

      if (c == last || *c != '/') {
        return init;
      }

      ++c; // skips first '/'

      if (c == last || *c != '/') {
        return init;
      }

      ++c; // skips second '/'

      c = try_parse_userinfo(c);
      c = try_parse_host(c);
      c = try_parse_port(c);

      return c;
    };

    auto try_parse_path = [&](auto init)
    {
      auto c = init;

      while (c != last && (grammar::is_pchar(*c) || *c == '/')) {
        path += *c++;
      }

      return c;
    };

    auto try_parse_query = [&](auto init)
    {
      auto c = init;

      if (c != last && *c == '?') {
        ++c; // skips '?'
        opt_query = std::string{};

        while (c != last && grammar::is_query(*c)) {
          *opt_query += *c++;
        }

        return c;
      }

      return init;
    };

    auto try_parse_fragment = [&](auto init)
    {
      auto c = init;

      if (c != last && *c == '#') {
        ++c; // skips '?#'

        opt_fragment = std::string{};

        while (c != last && grammar::is_fragment(*c)) {
          *opt_fragment += *c++;
        }

        return c;
      }

      return init;
    };

    first = try_parse_scheme(first);
    first = try_parse_authority(first);
    first = try_parse_path(first);
    first = try_parse_query(first);
    first = try_parse_fragment(first);

    if (first != last) {
      return std::nullopt;
    }

    auto percent_decode = [](std::string const& input)
    {
      auto hex_to_char = [](char c)
      {
        if (c>= '0' && c <= '9')
          return c - '0';

        if (c>= 'a' && c <= 'f')
          return c - 'a' + 10;

        if (c>= 'A' && c <= 'F')
          return c - 'A' + 10;

        throw std::invalid_argument{"invalid hex character"};
      };

      auto make_byte = [&](char a, char b)
      {
        return hex_to_char(a) << 4 | hex_to_char(b);
      };

      std::string str;

      auto j = input.begin();

      while (j != input.end()) {
        if ('%' == *j) {
          ++j;

          if (j == input.end()) {
            break;
          }

          char one = *j++;

          if (j == input.end()) {
            break;
          }

          char two = *j++;

          str += make_byte(one, two);

          continue;
        }

        str += *j;
        ++j;
      }

      return str;
    };

    if (opt_userinfo) {
      opt_userinfo = percent_decode(*opt_userinfo);
    }

    path = percent_decode(path);

    if (opt_query) {
      opt_query = percent_decode(*opt_query);
    }

    if (opt_fragment) {
      opt_fragment = percent_decode(*opt_fragment);
    }

    return uri_t{opt_scheme,
                 opt_userinfo,
                 opt_host,
                 opt_port,
                 path,
                 opt_query,
                 opt_fragment};
  }

} // namespace art::uri
