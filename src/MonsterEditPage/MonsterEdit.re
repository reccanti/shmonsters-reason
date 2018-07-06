/**
 * A component that handles the main field for editing
 * a monster
 */
open Utils;
open MonsterEditFields;
let component = ReasonReact.statelessComponent("MonsterEdit");

let make =
    (~monster: Store.monster, ~onUpdateField, ~onClickDelete, _children) => {
  ...component,
  render: _self =>
    <div className="MonsterEdit">
      <Link url="/"> (ReasonReact.string("<- Back")) </Link>
      <form>
        (
          monster.fields
          |> List.map((field: Store.field) =>
               <div className="EditField" key=(string_of_int(field.id))>
                 <Text
                   name=field.name
                   defaultValue=field.value
                   onValueChange=(value => onUpdateField((value, field)))
                 />
               </div>
             )
          |> Array.of_list
          |> ReasonReact.array
        )
      </form>
      <button className="EditField-button" onClick=(_ => onClickDelete())>
        (ReasonReact.string("Delete Monster"))
      </button>
    </div>,
};