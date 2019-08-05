#include <torch/csrc/distributed/rpc/Message.h>

namespace torch {
namespace distributed {
namespace rpc {

Message::Message() = default;

Message::Message(
    std::vector<char>&& meta,
    std::vector<torch::Tensor>&& tensors,
    MessageType type)
    : meta_(meta), tensors_(tensors), type_(type) {}

Message::Message(
    std::vector<char>&& meta,
    std::vector<torch::Tensor>&& tensors,
    MessageType type,
    int64_t id)
    : meta_(meta), tensors_(tensors), type_(type), id_(id) {}

Message::Message(const Message& other) = default;

Message::Message(Message&& other) noexcept = default;

Message& Message::operator=(Message const& rhs) & {
  auto meta = rhs.meta_;
  auto tensors = rhs.tensors_;
  Message(std::move(meta), std::move(tensors), rhs.type_, rhs.id_).swap(*this);
  return *this;
}

Message& Message::operator=(Message&& rhs) & {
  Message(std::move(rhs.meta_),
          std::move(rhs.tensors_),
          std::move(rhs.type_),
          rhs.id_).swap(*this);
  return *this;
}

void Message::swap(Message& rhs) noexcept {
  std::swap(meta_, rhs.meta_);
  std::swap(tensors_, rhs.tensors_);
  std::swap(type_, rhs.type_);
  std::swap(id_, rhs.id_);
}

const std::vector<char>& Message::meta() const {
  return meta_;
}

const std::vector<torch::Tensor>& Message::tensors() const {
  return tensors_;
}

const MessageType& Message::type() const {
  return type_;
}

bool Message::isRequest() const {
  return MessageType::SCRIPT_CALL == type_
      || MessageType::PYTHON_CALL == type_;
}

bool Message::isResponse() const {
  return MessageType::SCRIPT_RET == type_
      || MessageType::PYTHON_RET == type_;
}

bool Message::isShutdown() const {
  return MessageType::SHUTDOWN == type_;
}

int64_t Message::id() const {
  return id_;
}

void Message::setId(int64_t id) {
  id_ = id;
}


}
}
}
