[%bs.raw {|require('./MonsterList.css')|}];

type state = {
  monsters:
    list(
      Store.monsterRecord({
        .
        id: int,
        monster: Store.monster,
      }),
    ),
  inputRef: ref(option(Dom.element)),
};

type action =
  | AddMonster(string);

let component = ReasonReact.reducerComponent("MonsterList");

/**
 * sets the ref to the input element
 */
let setInputRef = (theRef, {ReasonReact.state}) =>
  state.inputRef := Js.Nullable.toOption(theRef);

/**
 * handles the Submit event that occurs when the user submits a monster name
 */
let handleSubmitMonster = (monsterName: string, {ReasonReact.send}) =>
  send(AddMonster(monsterName));

let make =
    (
      ~initialMonsters:
         list(
           Store.monsterRecord({
             .
             id: int,
             monster: Store.monster,
           }),
         ),
      _children,
    ) => {
  ...component,
  initialState: () => {monsters: initialMonsters, inputRef: ref(None)},
  reducer: (action: action, state: state) =>
    switch (action) {
    | AddMonster(name) =>
      let _newMonster =
        Store.addMonster({
          order: List.length(Store.getAllMonsters()),
          fields: [
            {id: 0, order: 0, name: "name", value: name},
            {id: 1, order: 1, name: "description", value: ""},
          ],
        });
      ReasonReact.Update({...state, monsters: Store.getAllMonsters()});
    },
  render: self =>
    <div>
      <MonsterListAddField onSubmit=(self.handle(handleSubmitMonster)) />
      <MonsterList monsters=self.state.monsters />
    </div>,
};