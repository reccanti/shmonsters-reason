/**
 * A component that handles the main field for editing
 * a monster
 */
open Utils;
open MonsterEditFields;
let component = ReasonReact.statelessComponent("MonsterEdit");

let make =
    (
      ~monster: Store.monster,
      ~initialDataUrl="",
      ~onUpdateField,
      ~onClickDelete,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className="MonsterEdit">
      <Link url="/"> (ReasonReact.string("<- Back")) </Link>
      <form className="MonsterEdit-form">
        <div className="EditField-section">
          <Canvas
            width="56"
            height="56"
            initialDataUrl
            onChange=(
              dataUrl =>
                onUpdateField((
                  dataUrl,
                  monster.fields
                  |> List.find((field: Store.field) =>
                       field.name == "portrait"
                     ),
                ))
            )
          />
        </div>
        <div>
          <div className="EditField-section">
            <div className="EditField-fieldList">
              (
                monster.fields
                |> List.filter((field: Store.field) =>
                     field.name != "portrait"
                   )  /* Ignore the portrait field, TODO: come up with a better solution */
                |> List.map((field: Store.field) =>
                     <div className="EditField" key=(string_of_int(field.id))>
                       <Text
                         name=field.name
                         defaultValue=field.value
                         onValueChange=(
                           value => onUpdateField((value, field))
                         )
                       />
                     </div>
                   )
                |> Array.of_list
                |> ReasonReact.array
              )
            </div>
          </div>
          <button className="EditField-button" onClick=(_ => onClickDelete())>
            (ReasonReact.string("Delete Monster"))
          </button>
        </div>
      </form>
    </div>,
};