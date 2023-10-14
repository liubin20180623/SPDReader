// Copyright (c) 2021 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_UI_COCOA_WINDOW_BUTTONS_PROXY_H_
#define SHELL_BROWSER_UI_COCOA_WINDOW_BUTTONS_PROXY_H_

#include <memory>
#import <Cocoa/Cocoa.h>
#include <QtCore/qpoint.h>

#include "scoped_nsobject.h"

@class WindowButtonsProxy;

// A helper view that floats above the window buttons.
@interface ButtonsAreaHoverView : NSView {
 @private
  WindowButtonsProxy* proxy_;
}
- (id)initWithProxy:(WindowButtonsProxy*)proxy;
@end

// Manipulating the window buttons.
@interface WindowButtonsProxy : NSObject {
 @private
  NSWindow* window_;

  // Current left-top margin of buttons.
  QPoint margin_;
  // The default left-top margin.
  QPoint default_margin_;

  // Track mouse moves above window buttons.
  BOOL show_on_hover_;
  BOOL mouse_inside_;
  scoped_nsobject<NSTrackingArea> tracking_area_;
  scoped_nsobject<ButtonsAreaHoverView> hover_view_;
}

- (id)initWithWindow:(NSWindow*)window;

- (void)setVisible:(BOOL)visible;
- (BOOL)isVisible;

// Only show window buttons when mouse moves above them.
- (void)setShowOnHover:(BOOL)yes;

// Set left-top margin of the window buttons..
- (void)setMargin:(const QPoint&)margin;

// Return the bounds of all 3 buttons, with margin on all sides.
- (NSRect)getButtonsContainerBounds;

- (void)redraw;
- (void)updateTrackingAreas;
@end

#endif  // SHELL_BROWSER_UI_COCOA_WINDOW_BUTTONS_PROXY_H_
