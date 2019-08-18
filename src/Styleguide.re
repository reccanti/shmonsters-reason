/**
 * The Styleguide page for the application. Used
 * to collect and document different components
 * that are in common use throughout the site
 */;

[@react.component]
let make = () => {
  let s = ReasonReact.string;
  <>
    <h1> (s(Strings.Styleguide.title)) </h1>
    <section>
      <h2> (s(Strings.Styleguide.Wrapper.title)) </h2>
      <p> (s(Strings.Styleguide.Wrapper.description)) </p>
    </section>
    <section>
      <h2> (s(Strings.Styleguide.Block.title)) </h2>
      <p> (s(Strings.Styleguide.Block.description)) </p>
      <Block> (s("Block Element")) </Block>
    </section>
    <section>
      <h2> (s(Strings.Styleguide.Canvas.title)) </h2>
      <p> (s(Strings.Styleguide.Canvas.description)) </p>
      <Block>
        <Canvas width="10" height="10" initialDataUrl="" onChange=(_s => ()) />
      </Block>
    </section>
  </>;
};