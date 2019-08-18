/**
 * Wrappings for the JsCanvas object
 */;

[@bs.module "./JsCanvas.js"] [@react.component]
external make :
  (
    ~width: string,
    ~height: string,
    ~initialDataUrl: string,
    ~onChange: string => unit
  ) =>
  React.element =
  "default";