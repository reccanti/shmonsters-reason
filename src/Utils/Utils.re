/**
 * A Link component inspired by the one in React Router
 */
module Link = {
  let component = ReasonReact.statelessComponent("Link");

  let make = (~url: string, children) => {
    ...component,
    render: _self =>
      <a
        href=url
        onClick=(
          e => {
            ReactEventRe.Synthetic.preventDefault(e);
            ReasonReact.Router.push(url);
          }
        )>
        (children |> ReasonReact.array)
      </a>,
  };
};