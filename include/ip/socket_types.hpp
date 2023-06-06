/*
 * Copyright (c) 2023 Runner-2019
 *
 * Licensed under the Apache License Version 2.0 with LLVM Exceptions
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *   https://llvm.org/LICENSE.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef IP_SOCKET_TYPES_HPP_
#define IP_SOCKET_TYPES_HPP_

#include <net/if.h>

#include <cstdint>

static constexpr int max_address_v4_string_len = 16;
static constexpr int max_address_v6_string_len = 256;
static constexpr int invalid_socket_fd = -1;
static constexpr int max_iov_len = 1024;
static constexpr int custom_socket_option_level = 0xA5100000;
static constexpr int enable_connection_aborted_option = 1;
static constexpr int always_fail_option = 2;

// The user wants a non-blocking socket.
static constexpr uint32_t non_blocking = 1;

// User wants connection_aborted errors, which are disabled by default.
static constexpr uint32_t enable_connection_aborted_state = 2;

// The user set the linger option. Needs to be checked when closing.
static constexpr uint32_t user_set_linger = 4;

// The socket is stream-oriented.
static constexpr uint32_t stream_oriented = 8;

// The socket is datagram-oriented.
static constexpr uint32_t datagram_oriented = 16;

// The socket may have been dup()-ed.
static constexpr uint32_t possible_dup = 32;

// The maximum length of the queue of pending incoming connections.
static constexpr int max_listen_connections = SOMAXCONN;

// The port type.
using port_type = uint_least16_t;

// The IPv6 scope id type.
using scope_id_type = uint_least16_t;

#endif  // IP_SOCKET_TYPES_HPP_
