import { faEraser, faMousePointer, faPencil, faPlus } from "@fortawesome/free-solid-svg-icons";
import EntityModal from "../../../../views/modals/entity";
import Button from "../../../../components/button";
import "./styles.scss";
import { useAppStore } from "../../../../store/app-store";

const EntitiesPalette = () => {
  const setModal = useAppStore((state) => state.setModal);
  return (
    <div className="entities-palette">
      <div className="entities-palette-buttons">
        <div className="entities-palette-buttons-row">
          <Button
            variant="primary"
            onClick={() => console.log("Add entity clicked!")}
            icon={faMousePointer}
          />
          <Button
            variant="primary"
            onClick={() => console.log("Add entity clicked!")}
            icon={faPencil}
          />
          <Button
            variant="primary"
            onClick={() => console.log("Add entity clicked!")}
            icon={faEraser}
          />
        </div>
        <div className="entities-palette-buttons-row">
          <Button
            variant="primary"
            onClick={() => setModal(<EntityModal />)}
            icon={faPlus}
          >
            New Entity
          </Button>
        </div>
      </div>
    </div>
  );
};

export default EntitiesPalette;
