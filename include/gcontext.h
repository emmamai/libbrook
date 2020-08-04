#ifndef _GCONTEXT_H_

typedef struct GContext {

} GContext;

void graphics_context_set_stroke_color( GContext* ctx, GColor color );
void graphics_context_set_fill_color( GContext* ctx, GColor color );
void graphics_context_set_text_color( GContext* ctx, GColor color );
void graphics_context_set_compositing_mode( GContext* ctx, GCompOp mode );
void graphics_context_set_antialiased( GContext* ctx, bool enable );
void graphics_context_set_stroke_width( GContext* ctx, uint8_t stroke_width );

#define _GCONTEXT_H_
#endif