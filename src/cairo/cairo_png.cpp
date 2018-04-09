//
// Created by xxzyjy on 2018/1/29.
//

#include <cairomm/cairomm.h>
#include <giomm.h>
#include <iostream>
#include "catch.hpp"

TEST_CASE("cairo_png", "[gtkmm]") {
//  Glib::init();
  Gio::init();

  auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 120, 120);
  auto cr = Cairo::Context::create(surface);

  cr->scale(120.0, 120.0);
  cr->set_line_width(0.1);
  cr->set_source_rgb(0.0, 0.0, 0.0);
  cr->rectangle(0.25, 0.25, 0.5, 0.5);
  cr->stroke();

  auto file = Gio::File::create_for_path("file.png");
  auto output_stream = file->create_file(Gio::FileCreateFlags::FILE_CREATE_REPLACE_DESTINATION);

  surface->write_to_png_stream([=](const unsigned char *data, unsigned int size) {
    try {
      output_stream->write(data, size);
      std::cout << "file.png created" << std::endl;
      return Cairo::ErrorStatus::CAIRO_STATUS_SUCCESS;
    } catch (const std::exception &error) {
      std::cout << "Error create file.png" << std::endl;
      return Cairo::ErrorStatus::CAIRO_STATUS_WRITE_ERROR;
    }
  });
}
