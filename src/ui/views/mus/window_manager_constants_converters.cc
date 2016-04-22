// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/mus/window_manager_constants_converters.h"

namespace mojo {

// static
mus::mojom::WindowType
TypeConverter<mus::mojom::WindowType, views::Widget::InitParams::Type>::Convert(
    views::Widget::InitParams::Type type) {
  switch (type) {
    case views::Widget::InitParams::TYPE_WINDOW:
      return mus::mojom::WINDOW_TYPE_WINDOW;
    case views::Widget::InitParams::TYPE_PANEL:
      return mus::mojom::WINDOW_TYPE_PANEL;
    case views::Widget::InitParams::TYPE_WINDOW_FRAMELESS:
      return mus::mojom::WINDOW_TYPE_WINDOW_FRAMELESS;
    case views::Widget::InitParams::TYPE_CONTROL:
      return mus::mojom::WINDOW_TYPE_CONTROL;
    case views::Widget::InitParams::TYPE_POPUP:
      return mus::mojom::WINDOW_TYPE_POPUP;
    case views::Widget::InitParams::TYPE_MENU:
      return mus::mojom::WINDOW_TYPE_MENU;
    case views::Widget::InitParams::TYPE_TOOLTIP:
      return mus::mojom::WINDOW_TYPE_TOOLTIP;
    case views::Widget::InitParams::TYPE_BUBBLE:
      return mus::mojom::WINDOW_TYPE_BUBBLE;
    case views::Widget::InitParams::TYPE_DRAG:
      return mus::mojom::WINDOW_TYPE_DRAG;
  }
  return mus::mojom::WINDOW_TYPE_POPUP;
}

}  // namespace mojo
