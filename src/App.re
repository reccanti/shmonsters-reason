/* [%bs.raw {|require('./App.css')|}]; */

[@bs.module] external logo : string = "./logo.svg";

type route = 
  | List
  | Edit;

type action = 
  | ChangeRoute(route);

type state = {
  route: route
};

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  reducer: (action, _state) =>
    switch action {
    | ChangeRoute(route) => ReasonReact.Update({ route: route })
    },
  initialState: () => { route: List },
  render: self => 
    <div>
      (
        switch (self.state.route) {
        | List => <MonsterList />
        | Edit => <MonsterEdit />
        }
      )
    </div>,
};
