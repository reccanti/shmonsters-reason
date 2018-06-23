type state = {
  monsterRecord:
    Store.monsterRecord({
      .
      id: int,
      monster: Store.monster,
    }),
};

type action =
  | UpdateField(Store.field)
  | SaveFields;

let component = ReasonReact.reducerComponent("MonsterEdit");

let make = (~id: int, _children) => {
  ...component,
  reducer: (action: action, state: state) =>
    switch (action) {
    | UpdateField(field) =>
      let updatedMonsterRecord =
        Store.updateMonster(
          ~id=state.monsterRecord#id,
          {
            ...state.monsterRecord#monster,
            fields:
              state.monsterRecord#monster.fields
              |> List.map((oldField: Store.field) =>
                   if (oldField.id == field.id) {
                     field;
                   } else {
                     oldField;
                   }
                 ),
          },
        );
      ReasonReact.Update({monsterRecord: updatedMonsterRecord});
    | _ => ReasonReact.NoUpdate
    },
  initialState: () => {monsterRecord: Store.getMonster(~id)},
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
          self.state.monsterRecord#monster.fields
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