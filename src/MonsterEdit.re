type field = {
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
    reducer: (action: action, _state: state) => {
        switch(action) {
        | _ => ReasonReact.NoUpdate
        }
    },
    initialState: () => 
        {monster: [
            { name: "name", value: "" },
            { name: "description", value: ""}
        ]},
    render: self => {
        <div>
        (
            self.state.monster
            |> List.map(field => <div>(ReasonReact.string(field.name ++ ": " ++ field.value))</div>)
            |> Array.of_list
            |> ReasonReact.array
              
        )
        </div>
    }
}