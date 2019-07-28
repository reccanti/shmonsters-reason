/**
 * A generic block that can be used to wrap content
 */;

[@react.component]
let make = (~children) =>
  <div
    className="border-width-4 border-style--solid border-color--light padding--16">
    children
  </div>;