/* [%bs.raw {|require('./App.css')|}]; */

[@bs.module] external logo : string = "./logo.svg";

type route =
  | List
  | Edit;

type action =
  | ChangeRoute(route);

type state = {route};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer: (action, _state) =>
    switch (action) {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    },
  initialState: () => {route: List},
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path) {
        | [_id, "edit"] => self.send(ChangeRoute(Edit))
        | _ => self.send(ChangeRoute(List))
        }
      );
    ();
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
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