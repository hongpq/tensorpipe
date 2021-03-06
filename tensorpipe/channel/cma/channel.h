/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <string>

#include <tensorpipe/channel/channel.h>
#include <tensorpipe/channel/cma/context.h>
#include <tensorpipe/channel/cpu_context.h>

namespace tensorpipe {
namespace channel {
namespace cma {

class Channel : public channel::CpuChannel {
  // Use the passkey idiom to allow make_shared to call what should be a private
  // constructor. See https://abseil.io/tips/134 for more information.
  struct ConstructorToken {};

 public:
  Channel(
      ConstructorToken,
      std::shared_ptr<Context::PrivateIface>,
      std::shared_ptr<transport::Connection> connection,
      std::string id);

  // Send memory region to peer.
  void send(
      CpuBuffer buffer,
      TDescriptorCallback descriptorCallback,
      TSendCallback callback) override;

  // Receive memory region from peer.
  void recv(TDescriptor descriptor, CpuBuffer buffer, TRecvCallback callback)
      override;

  // Tell the channel what its identifier is.
  void setId(std::string id) override;

  void close() override;

  ~Channel() override;

 private:
  class Impl;

  // Using a shared_ptr allows us to detach the lifetime of the implementation
  // from the public object's one and perform the destruction asynchronously.
  std::shared_ptr<Impl> impl_;

  // Allow context to access constructor token.
  friend class Context;
};

} // namespace cma
} // namespace channel
} // namespace tensorpipe
