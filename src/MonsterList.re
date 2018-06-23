type state = {
  monsters: list(Store.monsterRecord({. id: int, monster: Store.monster})), 
  inputRef: ref(option(Dom.element))
};

type action =
  | AddMonster(string);

let component = ReasonReact.reducerComponent("MonsterList");

let setInputRef = (theRef, {ReasonReact.state}) =>
  state.inputRef := Js.Nullable.toOption(theRef);


let handleSubmitMonster = (_e, {ReasonReact.state, ReasonReact.send}) => {
  switch (state.inputRef^) {
  | Some(element: Dom.element) => send(AddMonster(ReactDOMRe.domElementToObj(element)##value))
  | _ => ()
  }
};

let make = (~initialMonsters: list(Store.monsterRecord({. id: int, monster: Store.monster})), _children) => {
  ...component,
  initialState: () => {monsters: initialMonsters, inputRef: ref(None)},
  reducer: (action: action, state: state) =>
    switch (action) {
    | AddMonster(name) => {
      let _newMonster = Store.addMonster({
          order: List.length(Store.getAllMonsters()),
          fields: [
            {id: 0, order: 0, name: "name", value: name}, 
            {id: 1, order: 1, name: "description", value: ""}
          ],
        }); 
        ReasonReact.Update({...state, monsters: Store.getAllMonsters()});
      }
    },
  render: self =>
    <ul>
      (
        self.state.monsters
        |> List.map((monsterRecord: Store.monsterRecord({. id: int, monster: Store.monster})) =>
             <li key=(string_of_int(monsterRecord#id))>
               <a
                 href=("/" ++ string_of_int(monsterRecord#id) ++ "/edit")
                 onClick=(
                   e => {
                     ReactEventRe.Synthetic.preventDefault(e);
                     ReasonReact.Router.push(
                       "/" ++ string_of_int(monsterRecord#id) ++ "/edit",
                     );
                   }
                 )>
                 (
                   ReasonReact.string(
                     Store.getMonsterField(~id=monsterRecord#id, ~fieldName="name").
                       value,
                   )
                 )
               </a>
             </li>
           )
        |> Array.of_list
        |> ReasonReact.array
      )
      <li>
        <input ref={self.handle(setInputRef)} _type="text" name="newMonster" />
        <button onClick=(self.handle(handleSubmitMonster))>(ReasonReact.string("Add Monster"))</button>
      </li>
    </ul>,
};