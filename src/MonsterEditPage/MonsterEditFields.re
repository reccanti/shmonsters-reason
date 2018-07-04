/* module Text = {
       let component = ReasonReact.statelessComponent("Text");
       let make = (~name: string, _children) => {
       ...component,
       render: _self =>
           <label>
               <span className="EditField-label"> (ReasonReact.string(name)) </span>
               <input _type="text" className="EditField-input" name />
           </label>
   }; */
/* value=field.value
   onChange=(
     event =>
       self.send(
         UpdateField({
           ...field,
           value: ReactDOMRe.domElementToObj(
                    ReactEventRe.Form.target(event),
                  )##value,
         }),
       )
   ) */

/**
 * A component to render a standard text field
 */
module Text = {
  let component = ReasonReact.statelessComponent("Text");

  let handleTextChange = (e, onValueChange) => {
    let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value;
    onValueChange(value);
    ();
  };

  let make = (~name: string, ~defaultValue: string, ~onValueChange, _children) => {
    ...component,
    render: _self =>
      <label>
        <span className="EditField-label"> (ReasonReact.string(name)) </span>
        <input
          _type="text"
          className="EditField-input"
          name
          defaultValue
          onChange=(e => handleTextChange(e, onValueChange))
        />
      </label>,
  };
};