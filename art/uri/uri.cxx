#include <art/uri/uri.hxx>

#include <sstream>
#include <vector>
#include <iostream>

namespace art::uri
{

  uri_t::
  uri_t()
  {}

  uri_t::
  uri_t(std::string scheme, std::string host, std::string path)
    : scheme_{std::move(scheme)},
      host_{std::move(host)},
      path_{std::move(path)}
  {}

  uri_t::
  uri_t(std::string scheme,
        std::string host,
        std::string port,
        std::string path)
    : scheme_{std::move(scheme)},
      host_{std::move(host)},
      port_{std::move(port)},
      path_{std::move(path)}
  {}

  uri_t::
  uri_t(std::string scheme,
        std::string host,
        std::string port,
        std::string path,
        std::string query)
    : scheme_{std::move(scheme)},
      host_{std::move(host)},
      port_{std::move(port)},
      path_{std::move(path)},
      query_{std::move(query)}
  {}

  uri_t::
  uri_t(std::string scheme,
        std::string host,
        std::string port,
        std::string path,
        std::string query,
        std::string fragment)
    : scheme_{std::move(scheme)},
      host_{std::move(host)},
      port_{std::move(port)},
      path_{std::move(path)},
      query_{std::move(query)},
      fragment_{std::move(fragment)}
  {}

  uri_t::
  uri_t(std::string scheme,
        std::string userinfo,
        std::string host,
        std::string port,
        std::string path,
        std::string query,
        std::string fragment)
    : scheme_{std::move(scheme)},
      userinfo_{std::move(userinfo)},
      host_{std::move(host)},
      port_{std::move(port)},
      path_{std::move(path)},
      query_{std::move(query)},
      fragment_{std::move(fragment)}
  {}

  uri_t::
  uri_t(std::optional<std::string> scheme,
        std::optional<std::string> userinfo,
        std::optional<std::string> host,
        std::optional<std::string> port,
        std::string path,
        std::optional<std::string> query,
        std::optional<std::string> fragment)
    : scheme_{std::move(scheme)},
      userinfo_{std::move(userinfo)},
      host_{std::move(host)},
      port_{std::move(port)},
      path_{std::move(path)},
      query_{std::move(query)},
      fragment_{std::move(fragment)}
  {}

  std::optional<std::string> const&
  uri_t::
  scheme() const
  {
    return scheme_;
  }

  std::string
  uri_t::
  scheme_str() const
  {
    return scheme().value_or(std::string{});
  }

  std::optional<std::string> const&
  uri_t::
  userinfo() const
  {
    return userinfo_;
  }

  std::string
  uri_t::
  userinfo_str() const
  {
    return userinfo().value_or(std::string{});
  }

  std::optional<std::string> const&
  uri_t::
  host() const
  {
    return host_;
  }

  std::string
  uri_t::
  host_str() const
  {
    return host().value_or(std::string{});
  }

  std::optional<std::string> const&
  uri_t::
  port() const
  {
    return port_;
  }

  std::string
  uri_t::
  port_str() const
  {
    return port().value_or(std::string{});
  }

  std::string
  uri_t::
  path_str() const
  {
    return path_;
  }

  std::optional<std::string> const&
  uri_t::
  query() const
  {
    return query_;
  }

  std::string
  uri_t::
  query_str() const
  {
    return query().value_or(std::string{});
  }

  std::optional<std::string> const&
  uri_t::
  fragment() const
  {
    return fragment_;
  }

  std::string
  uri_t::
  fragment_str() const
  {
    return fragment().value_or(std::string{});
  }

  std::string
  to_string(uri_t const& uri)
  {
    std::ostringstream str;

    // Scheme
    //
    if (auto scheme = uri.scheme(); scheme) {
      str <<*scheme <<':';
    }

    // Authority
    //
    if (auto host = uri.host(); host) {
      str <<"//";

      // Userinfo
      //
      if (auto userinfo = uri.userinfo(); userinfo) {
        str <<*userinfo <<'@';
      }

      // Host
      //
      str <<*host;

      // Port
      if (auto port = uri.port(); port) {
        str <<':' <<*port;
      }
   }

    // Path
    //
    str <<uri.path_str();

    // Query
    //
    if (auto query = uri.query(); query) {
      str <<'?' <<*query;
    }

    // Fragment
    //
    if (auto fragment = uri.fragment(); fragment) {
      str <<'#' <<*fragment;
    }

    return str.str();
  }

  uri_t
  normalize_path(uri_t const& uri)
  {
    std::stringstream path{uri.path_str()};
    std::vector<std::string> segments;

    for (std::string segment; std::getline(path, segment, '/');) {
      std::cout << "found segment: " << segment << '\n';

      if (segment.empty()) {
        continue;
      }
      if (segment == ".") {
        continue;
      }
      if (segment == "..") {
        if (!segments.empty()) {
          segments.pop_back();
        }
        continue;
      }
      segments.push_back(segment);
    }

    std::string normalized;

    for (auto const& j : segments) {
      normalized += '/';
      normalized += j;
    }

    return uri_t{
      uri.scheme(),
      uri.userinfo(),
      uri.host(),
      uri.port(),
      normalized.empty() ? "/" : normalized,
      uri.query(),
      uri.fragment()
    };
  }

  std::optional<uri_t>
  try_parse(std::string const& str)
  {
    return try_parse(str.begin(), str.end());
  }

} // namespace uri
