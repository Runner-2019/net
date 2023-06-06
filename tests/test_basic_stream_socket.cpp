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
#include <optional>

#include "catch2/catch_test_macros.hpp"
#include "status-code/system_code.hpp"

#include "basic_stream_socket.hpp"
#include "mock_protocol.hpp"

TEST_CASE("[Default constructor]", "[basic_stream_socket.ctor]") {
  net::execution_context ctx{};
  net::basic_stream_socket<mock_protocol> socket{ctx};
  CHECK(!socket.is_open());
  CHECK(socket.state() == 0);
  CHECK(socket.protocol_ == std::nullopt);
}
