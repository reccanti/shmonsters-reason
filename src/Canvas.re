/**
 * Wrappings for the JsCanvas object
 */;
/* [@bs.deriving abstract]
   type jsProps = {
     width: string,
     height: string,
     initialDataUrl: string,
     onChange: string => unit,
   };

   [@bs.module "./JsCanvas"]
   external jsCanvas : ReasonReact.reactClass = "default";

   let make = (~width, ~height, ~initialDataUrl="", ~onChange, children) =>
     ReasonReact.wrapJsForReason(
       ~reactClass=jsCanvas,
       ~props=jsProps(~width, ~height, ~initialDataUrl, ~onChange),
       children,
     ); */

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