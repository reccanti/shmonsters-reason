[%bs.raw {|require('./MonsterEdit.css')|}];

type state = {monsterRecord: Store.monsterRecord};

type action =
  | UpdateField(Store.field)
  | SaveFields;

let component = ReasonReact.reducerComponent("MonsterEditPage");

/**
 * A helper function that creates a new monster type object
 * with the given field
 */
let createUpdatedMonster = (monster: Store.monster, field: Store.field) => {
  ...monster,
  fields:
    monster.fields
    |> List.map((oldField: Store.field) =>
         oldField.id == field.id ? field : oldField
       ),
};

/**
 * A handler for a text field's change event. Wraps the
 * necessary fields in a tuple and puts them in an UpdateField event
 */
let handleUpdateField =
    ((value: string, field: Store.field), {ReasonReact.send}) =>
  send(UpdateField({...field, value}));

/**
 * Get the monster if it exists. If it does not, create an empty monster
 */
/* let getInitialStateOrEmpty: int = id; */

let make = (~id=(-1), _children) => {
  ...component,
  reducer: (action: action, state: state) =>
    switch (action) {
    | UpdateField(field) =>
      let updatedMonsterRecord =
        Store.updateMonster(
          ~id=state.monsterRecord#id,
          createUpdatedMonster(state.monsterRecord#monster, field),
        );
      ReasonReact.Update({monsterRecord: updatedMonsterRecord});
    | _ => ReasonReact.NoUpdate
    },
  initialState: () => {monsterRecord: Store.getMonster(~id)},
  render: self =>
    <MonsterEdit
      onUpdateField=(self.handle(handleUpdateField))
      monster=self.state.monsterRecord#monster
    />,
};