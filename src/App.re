/* [%bs.raw {|require('./App.css')|}]; */

[@bs.module] external logo : string = "./logo.svg";

type route =
  | List
  | Edit(int);

type action =
  | ChangeRoute(route);

type state = {route};

let component = ReasonReact.reducerComponent("App");

/* Initial State */
Store.addMonster({
  id: 0,
  order: 0,
  fields: [
    {id: 0, order: 0, name: "name", value: "LeavesBuscemi"},
    {
      id: 1,
      order: 1,
      name: "description",
      value: "Has lovely foliage in the spring",
    },
  ],
});

Store.addMonster({
  id: 1,
  order: 1,
  fields: [
    {id: 0, order: 0, name: "name", value: "ViewScemi"},
    {id: 1, order: 1, name: "description", value: "This Buscemi sees all"},
  ],
});

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
        | [id, "edit"] => self.send(ChangeRoute(Edit(int_of_string(id))))
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
        | List => <MonsterList initialMonsters=(Store.getAllMonsters()) />
        | Edit(id) => <MonsterEdit id />
        }
      )
    </div>,
};