type state = {monsters: list(Store.monster)};

type action =
  | AddMonster(string);

let component = ReasonReact.reducerComponent("MonsterList");

let make = (~initialMonsters: list(Store.monster), _children) => {
  ...component,
  initialState: () => {monsters: initialMonsters},
  reducer: (action: action, state: state) =>
    switch (action) {
    | AddMonster(name) => {
      Store.addMonster({
          id: 1,
          order: 1,
          fields: [{id: 1, order: 1, name: "name", value: name}],
        }); 
        ReasonReact.Update({monsters: Store.getAllMonsters()});
      }
    },
  render: self =>
    <ul>
      (
        self.state.monsters
        |> List.map((monster: Store.monster) =>
             <li key=(string_of_int(monster.id))>
               <a
                 href=("/" ++ string_of_int(monster.id) ++ "/edit")
                 onClick=(
                   e => {
                     ReactEventRe.Synthetic.preventDefault(e);
                     ReasonReact.Router.push(
                       "/" ++ string_of_int(monster.id) ++ "/edit",
                     );
                   }
                 )>
                 (
                   ReasonReact.string(
                     Store.getMonsterField(~id=monster.id, ~fieldName="name").
                       value,
                   )
                 )
               </a>
             </li>
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </ul>,
};