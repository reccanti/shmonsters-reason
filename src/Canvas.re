
[@bs.deriving abstract]
type jsProps = {
    width: string,
    height: string
};

[@bs.module "./JsCanvas"] external jsCanvas: ReasonReact.reactClass = "default";

let make = (
    ~width="32",
    ~height="32",
    children
) => {
    ReasonReact.wrapJsForReason(
        ~reactClass=jsCanvas,
        ~props=jsProps(
            ~width="16", 
            ~height="16"
        ),
        children,
    );
};