#ifndef NODE_BSON_H
#define NODE_BSON_H
#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>

using namespace v8;

class ObjectID : public node::ObjectWrap {
    public:
    static v8::Persistent<v8::FunctionTemplate> constructor_template;

    static void Initialize(Handle<Object> target);

    ObjectID() : ObjectWrap() {}
    ~ObjectID() {}

    static Handle<Value> ToString(const Arguments &args);

    bson_oid_t get() { return oid; }
    void str(char *);
    protected:
    static Handle<Value> New(const Arguments& args) {
        HandleScope scope;

        String::Utf8Value hex(args[0]->ToString());
        // TODO assert ns != undefined (args.Length > 0)
        //
        // arg 1 is a string with the hex code

        ObjectID *o = new ObjectID((const char *)*hex);
        o->Wrap(args.This());
        return args.This();
    }


    ObjectID(const char *hex) : node::ObjectWrap() {
        bson_oid_from_string(&oid, hex);
    }

    private:

    bson_oid_t oid;
};

v8::Local<v8::Value> decodeObjectStr(const char *);
bson encodeObject(const v8::Local<v8::Value> element);

#endif
