import type { EntityPrototypeField } from "@app-types/entities";

import { faPlus, faCheck } from "@fortawesome/free-solid-svg-icons";
import Button from "../../../components/button";
import { useState } from "react";
import { PROPERTY_TYPES } from "@constants/entities";

const PropertyRow = () => {

  return (
    <div className="entity-modal-properties__row">
      <input className="entity-modal-properties__row-name" type="text" placeholder="Property name" />
      <select className="entity-modal-properties__row-type">
        <option value="string">String</option>
        <option value="number">Number</option>
        <option value="boolean">Boolean</option>
      </select>
      <Button 
        variant="primary"
        onClick={() => console.log('Remove property clicked!')} 
        icon={faPlus} />
    </div>
  )
}

const EntityModal = () => {
  const [newProperty, setNewProperty] = useState<EntityPrototypeField | null>(null);

  const handleAddNewProperty = () => {
    setNewProperty({
      name: "",
      type: 0,
      defaultValue: "",
    });
  };

  return (
    <div className="entity-modal">
      <input className="entity-modal" type="text" placeholder="Entity name" />
      <hr />
      <p>Properties</p>
      <div className="entity-modal-properties__header">
        <span>Properties</span>
        <Button 
          variant="primary"
          onClick={handleAddNewProperty} 
          icon={faPlus} />
      </div>
      <div className="entity-modal-properties__list">
        { 
          newProperty && (
          <div className="entity-modal-properties__add">
            <input type="text" placeholder="Property name" value={newProperty.name} onChange={(e) => setNewProperty({ ...newProperty, name: e.target.value })} />
            <select value={newProperty.type} onChange={(e) => setNewProperty({ ...newProperty, type: Number(e.target.value) })}>
              <option value={0} disabled>
                Select entity type
              </option>
              {PROPERTY_TYPES.map((propertyType, i) => (
                <option key={propertyType} value={i + 1}>
                  {propertyType}
                </option>
              ))}
            </select>
            <Button disabled={!newProperty.name || !newProperty.name.length || newProperty.type === 0} onClick={() => setNewProperty(null)} variant="primary" icon={faCheck} />
          </div>)
        }
        <PropertyRow />
      </div>
    </div>
  )
}

export default EntityModal;