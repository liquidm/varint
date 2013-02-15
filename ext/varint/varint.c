#include "ruby.h"

static VALUE Varint;
static ID getbyte, putbyte;

static VALUE varint_encode(VALUE module, VALUE io, VALUE int_valV)
{
    /* unsigned for the bit shifting ops */
    unsigned long long int_val = (unsigned long long)NUM2LL(int_valV);
    unsigned char byte;
    while (1) {
        byte = int_val & 0x7f;
        int_val >>= 7;
        if (int_val == 0) {
            rb_funcall(io, putbyte, 1, INT2FIX(byte));
            return Qnil;
        } else {
            rb_funcall(io, putbyte, 1, INT2FIX(byte | 0x80));
        }
    }
}

static VALUE varint_decode(VALUE module, VALUE io)
{
    unsigned long long int_val = 0;
    unsigned shift = 0;
    unsigned char byte;

    while (1) {
        if (shift >= 64) {
            rb_raise(rb_eArgError, "too many bytes when decoding varint");
        }
        byte = (unsigned char)FIX2INT(rb_funcall(io, getbyte, 0));
        int_val |= ((unsigned long long)(byte & 0x7f)) << shift;
        shift += 7;
        if ((byte & 0x80) == 0) {
            /* return ULL2NUM(int_val); */
            return LL2NUM((long long)int_val);
        }
    }
}

void Init_varint()
{
    Varint = rb_define_module("Varint");

    getbyte = rb_intern("getbyte");
    putbyte = rb_intern("putc");

    rb_define_method(Varint, "encode", varint_encode, 2);
    rb_define_method(Varint, "decode", varint_decode, 1);
}
