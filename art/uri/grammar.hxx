#ifndef art__uri__grammar_hxx_
#define art__uri__grammar_hxx_

namespace art::uri::grammar
{

  inline
  bool
  is_alpha(char c)
  {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
  }

  inline
  bool
  is_digit(char c)
  {
    return '0' <= c && c <= '9';
  }

  inline
  bool
  is_unreserved(char c)
  {
    if (is_alpha(c) || is_digit(c)) {
      return true;
    }

    switch (c) {
      case '-':
      case '.':
      case '_':
      case '~':
        return true;
    }

    return false;
  }

  inline
  bool
  is_subdelim(char c)
  {
    switch (c) {
      case '!':
      case '$':
      case '&':
      case '(':
      case ')':
      case '*':
      case '+':
      case ',':
      case ';':
      case '=':
      case '\'':
        return true;
    }

    return false;
  }

  inline
  bool
  is_scheme_start(char c)
  {
    return is_alpha(c);
  }

  inline
  bool
  is_scheme(char c)
  {
    return is_alpha(c) || is_digit(c) || c == '+' || c == '-' || c == '.';
  }

  inline
  bool
  is_userinfo(char c)
  {
    return is_unreserved(c) || is_subdelim(c) || c == ':' || c == '%';
  }

  inline
  bool
  is_regname(char c)
  {
    return is_unreserved(c) || is_subdelim(c);
  }

  inline
  bool
  is_host(char c)
  {
    return is_regname(c);
  }

  inline
  bool
  is_port(char c)
  {
    return is_digit(c);
  }

  inline
  bool
  is_pchar(char c)
  {
    return is_unreserved(c) || is_subdelim(c) || c == ':' || c == '@' || c == '%';
  }

  inline
  bool
  is_segment_nc(char c)
  {
    return is_pchar(c) && c != ':';
  }

  inline
  bool
  is_query(char c)
  {
    return is_pchar(c) || c == '/' || c == '?';
  }

  inline
  bool
  is_fragment(char c)
  {
    return is_pchar(c) || c == '/' || c == '?';
  }
} // namespace art::uri::grammar

#endif
