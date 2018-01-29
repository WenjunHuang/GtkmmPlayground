//
// Created by xxzyjy on 2018/1/29.
//

#include "catch.hpp"
#include <cairomm/cairomm.h>

TEST_CASE("cairo_pdf", "[cairo]") {
  auto ps = Cairo::PdfSurface::create("pdffile.pdf", 504, 648);
  auto cr = Cairo::Context::create(ps);

  cr->set_source_rgb(0,0,0);
  cr->select_font_face("Sans",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
  cr->set_font_size(40);

  cr->move_to(10,50);
  cr->show_text("Disziplin ist Macht.");
  cr->show_page();
}