import { faPlus } from "@fortawesome/free-solid-svg-icons";
import Button from "../../../../components/button";
import './styles.scss';

type Props = {
  options: string[];
};

const ScenePalette = ({options}: Props) => {
  return (
    <div className="palette">
      <select id="node-type-select" className="palette-select" defaultValue="task">
        {options.map((o) => (
          <option key={o} value={o}>
            {o}
          </option>
        ))}
      </select>
      <Button variant="primary" onClick={() => console.log('Button clicked!')} icon={faPlus} />
    </div>
  )
}

export default ScenePalette;