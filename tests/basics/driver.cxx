#include <art/uri/uri.hxx>

#include <art/validation/main.hxx>

#include <functional>
#include <memory>
#include <iostream>

VALIDATION_TEST(test_01)
{
  auto opt_uri = art::uri::try_parse("");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_FALSE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_FALSE((bool)uri.host());
  VALIDATION_ASSERT_FALSE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_TRUE(uri.path_str().empty());
}

VALIDATION_TEST(test_02)
{
  auto opt_uri = art::uri::try_parse("http:///index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), true);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), true);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), false);

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "http");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/index.html");
}

VALIDATION_TEST(test_03)
{
  auto opt_uri = art::uri::try_parse("http://host.domain./index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_TRUE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_FALSE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "http");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/index.html");
}

VALIDATION_TEST(test_04)
{
  auto opt_uri = art::uri::try_parse("https://host.domain.:8443/index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_TRUE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_TRUE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "https");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.port_str(), "8443");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/index.html");
}

VALIDATION_TEST(test_05)
{
  auto opt_uri = art::uri::try_parse("https://host.domain.:8443/secodeh?q=hamsters");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_TRUE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_TRUE((bool)uri.port());
  VALIDATION_ASSERT_TRUE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "https");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.port_str(), "8443");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/secodeh");
  VALIDATION_ASSERT_EQUAL(uri.query_str(), "q=hamsters");
}

VALIDATION_TEST(test_06)
{
  auto opt_uri = art::uri::try_parse("https://host.domain.:8443/secodeh?q=hamsters#results");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_TRUE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_TRUE((bool)uri.port());
  VALIDATION_ASSERT_TRUE((bool)uri.query());
  VALIDATION_ASSERT_TRUE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "https");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.port_str(), "8443");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/secodeh");
  VALIDATION_ASSERT_EQUAL(uri.query_str(), "q=hamsters");
  VALIDATION_ASSERT_EQUAL(uri.fragment_str(), "results");
}

VALIDATION_TEST(test_07)
{
  auto opt_uri = art::uri::try_parse(
    "https://admin:qwerty@host.domain.:8443/secodeh?q=hamsters#results"
  );

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_TRUE((bool)uri.scheme());
  VALIDATION_ASSERT_TRUE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_TRUE((bool)uri.port());
  VALIDATION_ASSERT_TRUE((bool)uri.query());
  VALIDATION_ASSERT_TRUE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.scheme_str(), "https");
  VALIDATION_ASSERT_EQUAL(uri.userinfo_str(), "admin:qwerty");
  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.port_str(), "8443");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/secodeh");
  VALIDATION_ASSERT_EQUAL(uri.query_str(), "q=hamsters");
  VALIDATION_ASSERT_EQUAL(uri.fragment_str(), "results");
}

VALIDATION_TEST(test_08)
{
  auto opt_uri = art::uri::try_parse("//host.domain./index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_FALSE((bool)uri.scheme());
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_TRUE((bool)uri.host());
  VALIDATION_ASSERT_FALSE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.host_str(), "host.domain.");
  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/index.html");
}

VALIDATION_TEST(test_09)
{
  auto opt_uri = art::uri::try_parse("/index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_FALSE((bool)uri.host());
  VALIDATION_ASSERT_FALSE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/index.html");
}

VALIDATION_TEST(test_10)
{
  auto opt_uri = art::uri::try_parse("index.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_FALSE((bool)uri.userinfo());
  VALIDATION_ASSERT_FALSE((bool)uri.host());
  VALIDATION_ASSERT_FALSE((bool)uri.port());
  VALIDATION_ASSERT_FALSE((bool)uri.query());
  VALIDATION_ASSERT_FALSE((bool)uri.fragment());

  VALIDATION_ASSERT_EQUAL(uri.path_str(), "index.html");
}

VALIDATION_TEST(test_11)
{
  auto opt_uri = art::uri::try_parse("/files/index:1.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), false);

  VALIDATION_ASSERT_EQUAL(uri.path_str(), "/files/index:1.html");
}

VALIDATION_TEST(test_12)
{
  auto opt_uri = art::uri::try_parse("files/index:1.html");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), false);

  VALIDATION_ASSERT_EQUAL(uri.path_str(), "files/index:1.html");
}

VALIDATION_TEST(test_13)
{
  auto opt_uri = art::uri::try_parse("?q=hamsters");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), true);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), false);

  VALIDATION_ASSERT_EQUAL(uri.query_str(), "q=hamsters");
}

VALIDATION_TEST(test_14)
{
  auto opt_uri = art::uri::try_parse("?q=hamsters#results");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), true);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), true);

  VALIDATION_ASSERT_EQUAL(uri.query_str(), "q=hamsters");
  VALIDATION_ASSERT_EQUAL(uri.fragment_str(), "results");
}

VALIDATION_TEST(test_15)
{
  auto opt_uri = art::uri::try_parse("#results");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), true);

  VALIDATION_ASSERT_EQUAL(uri.fragment_str(), "results");
}

VALIDATION_TEST(test_16)
{
  auto opt_uri = art::uri::try_parse("#results?gui-sort=asc");

  VALIDATION_ASSERT_TRUE((bool)opt_uri);

  auto uri = *opt_uri;

  VALIDATION_ASSERT_EQUAL((bool)uri.scheme(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.userinfo(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.host(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.port(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.query(), false);
  VALIDATION_ASSERT_EQUAL((bool)uri.fragment(), true);

  VALIDATION_ASSERT_EQUAL(uri.fragment_str(), "results?gui-sort=asc");
}

int
main(int argc, char* argv[])
{
  return art::validation::main(argc, argv);
}
