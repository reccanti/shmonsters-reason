/**
 * The main entrypoint of the app. It is responsible for performing
 * initialization and handling routing. In the future, this may prove
 * to be too messy, so some of this functionality may need to be
 * separated out.
 */

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <Wrapper>
    (
      switch (url.path) {
      | ["styleguide"] => <Styleguide />
      | _ => <Block> (ReasonReact.string("Page Not Found")) </Block>
      }
    )
  </Wrapper>;
};