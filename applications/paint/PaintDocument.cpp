#include "paint/PaintDocument.h"
#include "paint/PaintTool.h"

PaintDocument *paint_document_create(int width, int height, Color fill_color)
{
    PaintDocument *document = __create(PaintDocument);

    document->bitmap = Bitmap::create_shared(width, height).take_value();
    document->painter = Painter(document->bitmap);

    document->primary_color = COLOR_BLACK;
    document->secondary_color = COLOR_WHITE;

    document->tool = pencil_tool_create();

    document->painter.clear(fill_color);

    return document;
}

void paint_document_destroy(PaintDocument *document)
{
    document->painter.~Painter();
    document->bitmap = nullptr;

    free(document);
}

void paint_document_set_tool(PaintDocument *document, PaintTool *tool)
{
    if (document->tool->destroy)
        document->tool->destroy(document->tool);

    free(document->tool);

    document->tool = tool;
}
