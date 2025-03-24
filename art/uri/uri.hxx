#ifndef art__uri__uri_hxx_
#define art__uri__uri_hxx_

#include <art/uri/grammar.hxx>

#include <optional>
#include <stdexcept>
#include <string>

namespace art::uri
{

  class uri_t
  {
  public:
    uri_t();

    uri_t(std::string, std::string, std::string);

    uri_t(std::string, std::string, std::string, std::string);

    uri_t(std::string,
          std::string,
          std::string,
          std::string,
          std::string);

    uri_t(std::string,
          std::string,
          std::string,
          std::string,
          std::string,
          std::string);

    uri_t(std::string,
          std::string,
          std::string,
          std::string,
          std::string,
          std::string,
          std::string);

    uri_t(std::optional<std::string>,
          std::optional<std::string>,
          std::optional<std::string>,
          std::optional<std::string>,
          std::string,
          std::optional<std::string>,
          std::optional<std::string>);

    std::optional<std::string> const&
    scheme() const;

    std::string
    scheme_str() const;

    std::optional<std::string> const&
    userinfo() const;

    std::string
    userinfo_str() const;

    std::optional<std::string> const&
    host() const;

    std::string
    host_str() const;

    std::optional<std::string> const&
    port() const;

    std::string
    port_str() const;

    std::string
    path_str() const;

    std::optional<std::string> const&
    query() const;

    std::string
    query_str() const;

    std::optional<std::string> const&
    fragment() const;

    std::string
    fragment_str() const;

  private:
    std::optional<std::string> scheme_;
    std::optional<std::string> userinfo_;
    std::optional<std::string> host_;
    std::optional<std::string> port_;
    std::string path_;
    std::optional<std::string> query_;
    std::optional<std::string> fragment_;

  };

  std::string
  to_string(uri_t const&);

  uri_t
  normalize_path(uri_t const&);

  template<typename Iterator>
  std::optional<uri_t>
  try_parse(Iterator first, Iterator last);

  std::optional<uri_t>
  try_parse(std::string const&);

} // namespace art::uri

#include <art/uri/uri.txx>

#endif
