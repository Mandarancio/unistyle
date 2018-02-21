
#include "renderer_css.h"


static void
rndr_doc(UniStr   *buf,
         Element  *doc,
         Renderer *rndr)
{
  unistr_puts(buf, "body {\n");
  /* TODO do your magic */
  unistr_puts(buf, "\tmargin: auto;\n"
                   "\tmax-width: 210mm;\n"); /* A4 size */
  PrefList *el;
  for (el = doc->list; el != NULL; el = el->next){
    rndr->preference(buf, el->preference, rndr);
  }
  /* END */
  unistr_puts(buf, "}\n");
}

static void
rndr_el(UniStr *buf,
        char   *id,
        PrefList *list,
        Renderer *rndr)
{
  unistr_printf(buf, "%s {\n", id);
  /* TODO do your magic */
  PrefList *el;
  for (el = list; el != NULL; el = el->next){
    rndr->preference(buf, el->preference, rndr);
  }
  /* END */
  unistr_puts(buf, "}\n");
}

static void
rndr_element (UniStr  *buffer,
              Element *element,
              void    *rndr)
{
  switch (element->type)
  {
  case DOCUMENT:
    rndr_doc(buffer, element, (Renderer*)rndr);
    break;
  case H1:
    rndr_el(buffer, "h1", element->list, (Renderer*)rndr);
    break;
  default:
    break;
  }
}

static void
rndr_pref (UniStr     *buf,
           const char *id_str,
           Preference *pre,
           Renderer   *rnd)
{
  unistr_printf(buf, "\t%s: ", id_str);
  rnd->value(buf, pre->value, rnd);
  unistr_puts(buf, ";\n");
}

static void
rndr_preference (UniStr     *buffer,
                 Preference *preference,
                 void       *rndr)
{
  if (preference->value->type == CATEGORY){
    PrefList * el = (PrefList*) preference->value->raw;
    for (; el != NULL; el = el->next)
    {
      rndr_preference(buffer, el->preference, rndr);
    }
    return;
  }
  switch (preference->type)
  {
  case COLOR:
    rndr_pref (buffer, "color", preference, (Renderer*)rndr);
    break;
  case BACKGROUND:
    rndr_pref (buffer, "background", preference, (Renderer*)rndr);
    break;
  case TEXT_ALIGN:
    rndr_pref (buffer, "text-align", preference, (Renderer*)rndr);
    break;
  case MARGIN:
    rndr_pref (buffer, "padding", preference, (Renderer*)rndr);
    break;
  case FONT_SIZE:
    rndr_pref (buffer, "font-size", preference, (Renderer*)rndr);
    break;
  case FONT_WEIGHT:
    rndr_pref (buffer, "font-weight", preference, (Renderer*)rndr);
    break;
  case MARGIN_BOTTOM:
    rndr_pref (buffer, "padding-bottom", preference, (Renderer*)rndr);
    break;
  case MARGIN_TOP:
    rndr_pref (buffer, "padding-top", preference, (Renderer*)rndr);
    break;
  case MARGIN_LEFT:
    rndr_pref (buffer, "padding-left", preference, (Renderer*)rndr);
    break;
  case MARGIN_RIGHT:
    rndr_pref (buffer, "padding-right", preference, (Renderer*)rndr);
    break;
  case COLUMNS:
    rndr_pref (buffer, "columns", preference, (Renderer*)rndr);
    break;
  default:
    break;
  }
}

static void
rndr_value (UniStr *buffer,
            Value  *value,
            void   *rndr)
{
  if (value->type == STRING)
  {
    unistr_printf(buffer, "%s", (char*) value->raw);
  }
}

Renderer
css_renderer()
{
  Renderer renderer = {
    rndr_element,
    rndr_preference,
    rndr_value
  };
  return renderer;
}
