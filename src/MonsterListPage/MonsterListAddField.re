[%bs.raw {|require('./AddField.css')|}];
let component = ReasonReact.statelessComponent("MonsterListAddField");

/**
 * This will be used to hold a ref to our input element
 */
let inputRef: ref(option('a)) = ref(None);

/**
 * sets the ref to the input element
 */
let setInputRef = theRef => inputRef := Js.Nullable.toOption(theRef);

/**
* Extracts information from a DOM element and sends an AddMonster event
*/
let handleSubmitMonster = (_e, onSubmit) =>
  switch (inputRef^) {
  | Some((element: Dom.element)) =>
    onSubmit(ReactDOMRe.domElementToObj(element)##value)
  | _ => ()
  };

let make = (~onSubmit, _children) => {
  ...component,
  render: _self =>
    <div className="AddField">
      <input
        className="AddField-input"
        ref=setInputRef
        _type="text"
        name="newMonster"
      />
      <button
        className="AddField-button"
        onClick=(_e => handleSubmitMonster(_e, onSubmit))>
        (ReasonReact.string("Add Monster"))
      </button>
    </div>,
};