// Copyright 2023 MyLib Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mylib/mylib.h"

namespace mylib {

int Calculator::Add(int a, int b) const {
  return a + b;
}

int Calculator::Subtract(int a, int b) const {
  return a - b;
}

std::string Calculator::GetVersion() {
  return "0.1.0";
}

}  // namespace mylib