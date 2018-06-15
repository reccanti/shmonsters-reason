type field = {
  id: int,
  name: string,
  value: string,
};

type monster = list(field);

type state = {monster};

type action =
  | AddField(field)
  | UpdateField(field)
  | SaveFields;

let component = ReasonReact.reducerComponent("MonsterEdit");

let make = _children => {
  ...component,
  reducer: (action: action, state: state) =>
    switch (action) {
    | UpdateField(field) =>
      ReasonReact.Update({
        monster:
          List.map(
            oldField =>
              if (oldField.id == field.id) {
                field;
              } else {
                oldField;
              },
            state.monster,
          ),
      })
    | _ => ReasonReact.NoUpdate
    },
  initialState: () => {
    monster: [
      {id: 0, name: "name", value: ""},
      {id: 1, name: "description", value: ""},
    ],
  },
  render: self =>
    <form>
      (
        self.state.monster
        |> List.map(field =>
             <div>
               <label>
                 (ReasonReact.string("name"))
                 <input
                   _type="text"
                   name=field.name
                   value=field.name
                   onChange=(
                     event =>
                       self.send(
                         UpdateField({
                           ...field,
                           name: ReactDOMRe.domElementToObj(
                                   ReactEventRe.Form.target(event),
                                 )##value,
                         }),
                       )
                   )
                 />
               </label>
               <label>
                 (ReasonReact.string("value"))
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
    </form>,
};