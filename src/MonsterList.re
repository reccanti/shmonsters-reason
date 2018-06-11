type monster = {
    name: string,
    description: string,
};

let testMonsters = [|
    {
        name: "ViewScemi",
        description: "This Buscemi can see everything"
    },
    {
        name: "Leaves Buscemi",
        description: "Has lovely foliage in the spring"
    }
|]

let component = ReasonReact.statelessComponent("MonsterList");

let make = (~monsters=testMonsters, _children) => {
    ...component,
    render: _self => {
        let monsterItems = Array.map(monster => <li>{ReasonReact.string(monster.name)}</li>, monsters);
        <ul>
            {ReasonReact.array(monsterItems)}
        </ul>
    },
}