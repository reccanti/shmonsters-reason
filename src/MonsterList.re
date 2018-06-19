let component = ReasonReact.statelessComponent("MonsterList");

let make = (~monsters: list(Store.monster), _children) => {
  ...component,
  render: _self =>
    <ul>
      (
        monsters
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