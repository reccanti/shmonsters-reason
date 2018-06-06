type state = {
    clicked: int,
    hovered: int,
};

type action =
| Click
| Hover;

let component = ReasonReact.reducerComponent("Canvas");
  
let make = (~width="32", ~height="32", _children) => {
    ...component,
    initialState: () => {clicked: 0, hovered: 0},
    reducer: (action, state) =>
        switch (action) {
        | Click => ReasonReact.Update({...state, clicked: state.clicked + 1})
        | Hover => ReasonReact.Update({...state, hovered: state.hovered + 1})
        },
    render: self => {
        <canvas 
        width 
        height 
        onClick=(_event => self.send(Click)) 
        onMouseMove=(_event => self.send(Hover)) 
        /> 
    },
}; 