#pragma once

#include "json.h"
#include <stack>
#include <string>
#include <memory>

namespace transport_catalogue {
    namespace detail {
        namespace json {
            namespace builder {

                class KeyContext;

                class DictionaryContext;

                class ArrayContext;

                class Builder {
                public:
                    Node MakeNode(const Node::Value &value_);

                    void AddNode(const Node &node);

                    KeyContext Key(const std::string &key_);

                    Builder &Value(const Node::Value &value_);

                    DictionaryContext StartDict();

                    Builder &EndDict();

                    ArrayContext StartArray();

                    Builder &EndArray();

                    Node Build();

                private:
                    Node root_;
                    std::vector<std::unique_ptr<Node>> nodes_stack_;
                };

                class BaseContext {
                public:
                    BaseContext(Builder &builder);

                    KeyContext Key(const std::string &key);

                    Builder &Value(const Node::Value &value);

                    DictionaryContext StartDict();

                    Builder &EndDict();

                    ArrayContext StartArray();

                    Builder &EndArray();

                protected:
                    Builder &builder_;
                };

                class KeyContext : public BaseContext {
                public:
                    KeyContext(Builder &builder);

                    KeyContext Key(const std::string &key) = delete;

                    BaseContext end_dict() = delete;

                    BaseContext end_array() = delete;

                    DictionaryContext Value(const Node::Value &value);
                };

                class DictionaryContext : public BaseContext {
                public:
                    DictionaryContext(Builder &builder);

                    DictionaryContext StartDict() = delete;

                    ArrayContext StartArray() = delete;

                    Builder &EndArray() = delete;

                    Builder &Value(const Node::Value &value) = delete;
                };

                class ArrayContext : public BaseContext {
                public:
                    ArrayContext(Builder &builder);

                    KeyContext Key(const std::string &key) = delete;

                    Builder &EndDict() = delete;

                    ArrayContext value(const Node::Value &value);
                };
            }
        }
    }
}