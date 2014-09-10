#ifndef HANDLER_HPP
#define HANDLER_HPP

// v8
#include <v8.h>

// node.js
#include <node_object_wrap.h>

// node-osmium
#include "osm_object_wrap.hpp"

namespace node_osmium {

    class JSHandler : public node::ObjectWrap {

        void print_error_message(v8::TryCatch& trycatch);

    public:

        static v8::Persistent<v8::FunctionTemplate> constructor;
        static void Initialize(v8::Handle<v8::Object> target);
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> on(const v8::Arguments& args);
        static v8::Handle<v8::Value> options(const v8::Arguments& args);
        JSHandler();

        void dispatch_object(const input_iterator& it);

        void init();
        void before_nodes();
        void after_nodes();
        void before_ways();
        void after_ways();
        void before_relations();
        void after_relations();
        void before_changesets();
        void after_changesets();
        void done();

        bool node_callback_for_tagged_only;

        v8::Persistent<v8::Function> init_cb;

        v8::Persistent<v8::Function> before_nodes_cb;
        v8::Persistent<v8::Function> node_cb;
        v8::Persistent<v8::Function> after_nodes_cb;

        v8::Persistent<v8::Function> before_ways_cb;
        v8::Persistent<v8::Function> way_cb;
        v8::Persistent<v8::Function> after_ways_cb;

        v8::Persistent<v8::Function> before_relations_cb;
        v8::Persistent<v8::Function> relation_cb;
        v8::Persistent<v8::Function> after_relations_cb;

        v8::Persistent<v8::Function> before_changesets_cb;
        v8::Persistent<v8::Function> changeset_cb;
        v8::Persistent<v8::Function> after_changesets_cb;

        v8::Persistent<v8::Function> done_cb;

    private:

        ~JSHandler();

    }; // class JSHandler

} // namespace node_osmium

#endif // HANDLER_HPP