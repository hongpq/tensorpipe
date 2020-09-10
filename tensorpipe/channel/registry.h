/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <tensorpipe/channel/context.h>
#include <tensorpipe/common/tensor.h>
#include <tensorpipe/util/registry/registry.h>

TP_DECLARE_SHARED_REGISTRY(
    TensorpipeChannelRegistry,
    tensorpipe::channel::CpuContext);
