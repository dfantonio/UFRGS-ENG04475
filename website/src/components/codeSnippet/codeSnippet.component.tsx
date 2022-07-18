import { Line } from "./codeSnippet.style";

type CodeSnippetProps = {
  [register: string]: string;
};

export const CodeSnippet = ({ configObj = [] }: any) => {
  const elements = Object.keys(configObj).map((item) => {
    return (
      <Line>
        {item} = {configObj[item]}
        <br></br>
      </Line>
    );
  });

  return <div>{elements.map((item) => item)}</div>;
};
