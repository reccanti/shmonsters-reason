/**
 * Container for all strings so that they aren't scattered
 * throughout the app
 */
module Styleguide = {
  let title = "Styleguide";

  module Wrapper = {
    let title = "Wrapper";
    let description = "a general purpose wrapper that applies a max-width and some padding. Meant to be used around the whole page";
  };

  module Block = {
    let title = "Block";
    let description = "a general-purpose wrapper component that applies a border and some padding around some content";
  };

  module Canvas = {
    let title = "Canvas";
    let description = "a component that lets you draw pixelated graphics. You can set the width and height of the canvas, and the color that gets drawn on it. It also provides various event handler props that allows you respond to these events";
  };
};