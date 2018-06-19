type state = {monster: Store.monster};

type action =
  | UpdateField(Store.field)
  | SaveFields;

let component = ReasonReact.reducerComponent("MonsterEdit");

let make = (~id: int, _children) => {
  ...component,
  reducer: (action: action, state: state) =>
    switch (action) {
    | UpdateField(field) =>
      let updatedMonster =
        Store.updateMonster(
          ~id=state.monster.id,
          {
            ...state.monster,
            fields:
              state.monster.fields
              |> List.map((oldField: Store.field) =>
                   if (oldField.id == field.id) {
                     field;
                   } else {
                     oldField;
                   }
                 ),
          },
        );
      ReasonReact.Update({monster: updatedMonster});
    | _ => ReasonReact.NoUpdate
    },
  initialState: () => {monster: Store.getMonster(~id)},
  render: self =>
    <div>
      <a
        href="/"
        onClick=(
          e => {
            ReactEventRe.Synthetic.preventDefault(e);
            ReasonReact.Router.push("/");
          }
        )>
        (ReasonReact.string("<- Back"))
      </a>
      <form>
        (
          self.state.monster.fields
          |> List.map((field: Store.field) =>
               <div key=(string_of_int(field.id))>
                 <label>
                   (ReasonReact.string(field.name))
                   <input
                     _type="text"
                     name=field.name
                     value=field.value
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
                     )
                   />
                 </label>
               </div>
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </form>
    </div>,
};