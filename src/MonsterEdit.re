/* type field = {
    name: string,
    value: string,
};

type monster = list(field);

type state = {
    monster: monster
}

type action = 
  | AddField(field)
  | SaveFields;

let component = ReasonReact.reducerComponent("MonsterEdit");

let make = (_children) => {
    ...component,
    reducer: (action, _state) => {
        switch(action) {
        | _ => ReasonReact.NoUpdate
        }
    },
    initialState: () => 
        {monster: [
            { name: "name", value: "" },
            { name: "description", value: ""}
        ]},
    render: _self => {
        <div>(ReasonReact.string("hello"))</div>
    }
} */

let component = ReasonReact.statelessComponent("MonsterEdit");

let make = (_children) => {
    ...component,
    render: _self => <div>(ReasonReact.string("ello")</div>)
}