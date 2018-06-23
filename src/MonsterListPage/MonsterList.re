open Utils;

let component = ReasonReact.statelessComponent("MonsterList");

let make =
    (
      ~monsters:
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
  render: _self =>
    <ol className="MonsterList">
      (
        monsters
        |> List.map(
             (
               monsterRecord:
                 Store.monsterRecord({
                   .
                   id: int,
                   monster: Store.monster,
                 }),
             ) =>
             <li
               className="MonsterList-item"
               key=(string_of_int(monsterRecord#id))>
               <Link url=("/" ++ string_of_int(monsterRecord#id) ++ "/edit")>
                 (
                   ReasonReact.string(
                     Store.getMonsterField(
                       ~id=monsterRecord#id,
                       ~fieldName="name",
                     ).
                       value,
                   )
                 )
               </Link>
             </li>
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </ol>,
};