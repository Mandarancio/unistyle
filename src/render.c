#include "unistyle.h"
#include "renderer_cls.h"
#include "renderer_css.h"

char
*render (Style         *style,
         Renderer       renderer)
{
  UniStr * buff = unistr_new();
  ElemList * el;
  for (el = style->list; el != NULL; el = el->next)
  {
    renderer.element(buff, el->el, &renderer);
  }
  return buff->data;
}

char
*render_css (Style         *style)
{
  return render(style, css_renderer());
}

char
*render_cls (Style         *style)
{
  return render(style, cls_renderer());
}
