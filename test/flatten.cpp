//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2018-25, Lawrence Livermore National Security, LLC
// and Camp project contributors. See the camp/LICENSE file for details.
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//See the LLVM_LICENSE file at http://github.com/llnl/camp for the full license
//text.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <camp/camp.hpp>

using namespace camp;
CAMP_CHECK_TSAME((flatten<list<>>), (list<>));
CAMP_CHECK_TSAME((flatten<list<int>>), (list<int>));
CAMP_CHECK_TSAME((flatten<list<list<int>>>), (list<int>));
CAMP_CHECK_TSAME((flatten<list<list<list<int>>>>), (list<int>));
CAMP_CHECK_TSAME((flatten<list<float, list<int, double>, list<list<int>>>>),
    (list<float, int, double, int>));

