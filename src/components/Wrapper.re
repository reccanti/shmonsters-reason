/**
 * A wrapper that applies a max-width
 */;

[@react.component]
let make = (~children) =>
  <main className="maxWidth--1000 center padding--16 stack--4">
    children
  </main>;