type monster = {
  id: int,
  name: string,
  description: string,
};

let testMonsters = [|
  {id: 0, name: "ViewScemi", description: "This Buscemi can see everything"},
  {
    id: 1,
    name: "Leaves Buscemi",
    description: "Has lovely foliage in the spring",
  },
|];

let component = ReasonReact.statelessComponent("MonsterList");

let make = (~monsters=testMonsters, _children) => {
  ...component,
  render: _self =>
    <ul>
      (
        monsters
        |> Array.map(monster =>
             <li>
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
                 (ReasonReact.string(monster.name))
               </a>
             </li>
           )
        |> ReasonReact.array
      )
    </ul>,
};