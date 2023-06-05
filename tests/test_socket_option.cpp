#include <netinet/in.h>
#include <catch2/catch_test_macros.hpp>
#include <cstring>

#include "socket_option.hpp"

using namespace net::socket_option;

class MockProtocol {};

TEST_CASE("[default ctor of boolean]", "[socket_option.boolean.ctor]") {
  boolean<SOL_SOCKET, SO_REUSEADDR> option{1};
  MockProtocol protocol;

  // on
  CHECK(option.level(protocol) == SOL_SOCKET);
  CHECK(option.name(protocol) == SO_REUSEADDR);
  CHECK(option.value());
  CHECK(option.size(protocol) == sizeof(int));
  int* data = option.data(protocol);
  CHECK(data != nullptr);
  CHECK(*data == 1);

  // off
  boolean<SOL_SOCKET, SO_DEBUG> option_off{0};
  CHECK(option_off.level(protocol) == SOL_SOCKET);
  CHECK(option_off.name(protocol) == SO_DEBUG);
  CHECK(!option_off.value());
  CHECK(option_off.size(protocol) == sizeof(int));
  data = option_off.data(protocol);
  CHECK(data != nullptr);
  CHECK(*data == 0);
}

TEST_CASE("[setsocketopt with boolean should work]", "[socket_option.boolean]") {
  boolean<SOL_SOCKET, SO_REUSEADDR> option{1};
  MockProtocol protocol;

  int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  CHECK(fd != -1);
  CHECK(::setsockopt(fd,
                     option.level(protocol),  //
                     option.name(protocol),   //
                     option.data(protocol),   //
                     option.size(protocol))
        == 0);
}

TEST_CASE("[default ctor of integer]", "[socket_option.integer.ctor]") {
  integer<SOL_SOCKET, SO_DEBUG> option{1};
  MockProtocol protocol;

  // on
  CHECK(option.level(protocol) == SOL_SOCKET);
  CHECK(option.name(protocol) == SO_DEBUG);
  CHECK(option.value());
  CHECK(option.size(protocol) == sizeof(int));
  int* data = option.data(protocol);
  CHECK(data != nullptr);
  CHECK(*data == 1);

  // off
  boolean<SOL_SOCKET, SO_DEBUG> option_off{0};
  CHECK(option_off.level(protocol) == SOL_SOCKET);
  CHECK(option_off.name(protocol) == SO_DEBUG);
  CHECK(!option_off.value());
  CHECK(option_off.size(protocol) == sizeof(int));
  data = option_off.data(protocol);
  CHECK(data != nullptr);
  CHECK(*data == 0);
}

TEST_CASE("[setsocketopt with integer should work]", "[socket_option.integer]") {
  integer<SOL_SOCKET, SO_REUSEADDR> option{1};
  MockProtocol protocol;

  int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  CHECK(fd != -1);

  int opt_on = 1;
  CHECK(::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt_on, sizeof(opt_on)) == 0);
  CHECK(::setsockopt(fd,
                     option.level(protocol),  //
                     option.name(protocol),   //
                     option.data(protocol),   //
                     option.size(protocol))
        == 0);
  // std::cout << ::strerror(errno) << std::endl;
}
