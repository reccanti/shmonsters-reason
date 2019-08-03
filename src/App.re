/**
 * The main collection of initializers for the app
 */

[@react.component]
let make = () =>
  <Wrapper>
    <Block>
      <Canvas
        width="56"
        height="56"
        initialDataUrl=""
        onChange=(_string => ())
      />
    </Block>
  </Wrapper>;